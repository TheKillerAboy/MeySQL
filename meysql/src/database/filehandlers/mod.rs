use indexmap::set::IndexSet;
use std::collections::BTreeSet;
use std::path::Path;
use std::fs::OpenOptions;

use positioned_io::{RandomAccessFile,ReadAt,WriteAt};

use crate::Result;

pub type FAddress = u64;

pub struct FileHandler{
    pub file: RandomAccessFile,
    pub last: FAddress,
    pub queue_l: IndexSet<FAddress>,
    pub queue_r: IndexSet<FAddress>
}

impl FileHandler {
    pub fn open<P: AsRef<Path>>(path: P) -> Result<FileHandler>{
        let file = OpenOptions::new().write(true).read(true).open(path)?;
        let len = file.metadata().unwrap().len();
        let file = RandomAccessFile::try_new(file)?;
        let mut handler = FileHandler{file: file, last:len, queue_l: IndexSet::new(), queue_r: IndexSet::new()};        
        if len != 0{
            let (mut next, addr) = FAddress::load(&handler, 0)?;
            let (_addr, amount) = u64::load(&handler, next)?;
            next = addr;
            for _ in 0..amount{
                let (addr, clean_addr) = FAddress::load(&handler, next)?;
                handler.queue_l.insert(clean_addr);
                let (addr, clean_addr) = FAddress::load(&handler, addr)?;
                handler.queue_r.insert(clean_addr);
                next = addr;
            }
        }
        else{
            handler.last = FileHandler::front()?;
        }
        Ok(handler)
    }
    pub fn front() -> Result<FAddress>{
        Ok(FAddress::size()? + u64::size()?)
    }
    pub fn allocate(&mut self, size: u64) -> Result<FAddress>{
        // TODO: Add checking of queue for space
        let out = self.last.clone();
        self.last += size;
        Ok(out)
    }
    pub fn load_slice(&self, addr: FAddress, size: u64) -> Result<(FAddress, Vec<u8>)>{
        let mut slice: Vec<u8> = vec![0;size as usize];
        self.file.read_at(addr, &mut slice)?;
    
        Ok((addr + size, slice))
    }
    pub fn dump_slice(&mut self, addr: FAddress, data:Vec<u8>) -> Result<FAddress>{
        self.file.write_at(addr, &data)?;
    
        Ok(addr + (data.len() as FAddress))
    }
    pub fn close(&mut self) -> Result<()>{
        let queue_addr = self.last;
        let queue_len = self.queue_l.len() as u64;
        let queue_len_addr = FAddress::dump_allocated(self, 0, queue_addr)?;
        u64::dump_allocated(self, queue_len_addr, queue_len)?;
        let mut addr = queue_addr;
        for i in 0..self.queue_l.len(){
            addr = FAddress::dump_allocated(self,addr,self.queue_l[i].clone())?;
            addr = FAddress::dump_allocated(self,addr,self.queue_r[i].clone())?;
        }
        Ok(())
    }
    pub fn delete_range(&mut self, l: FAddress, s: u64) -> Result<()>{
        match self.queue_l.get_index_of(&(l+s)){
            Some(i) => {
                self.queue_l.remove(&(l+s));
                self.queue_l.insert(l);
                return Ok(());
            }
            _ => {}
        }
        match self.queue_r.get_index_of(&(l-1)){
            Some(i) => {
                self.queue_r.remove(&(l-1));
                self.queue_r.insert(l+s-1);
                return Ok(());
            }
            _ => {}
        }
        self.queue_l.insert(l);
        self.queue_r.insert(l+s-1);
        Ok(())
    }
}

pub trait FileHandle{
    type T;
    fn size() -> Result<u64>;
    fn from_bytes(slice: Vec<u8>) -> Result<Self::T>;
    fn to_bytes(data: Self::T) -> Result<Vec<u8>>;
    fn load(handler: &FileHandler, addr: FAddress) -> Result<(FAddress, Self::T)>
    where Self::T:std::fmt::Debug{
        let (addr, slice) = handler.load_slice(addr, Self::size()?)?;
        let data = Self::from_bytes(slice)?;
        log::debug!("Loading data at address {}: {:?}", addr, data);
        Ok((addr, data))
    }
    fn dump(handler: &mut FileHandler, data: Self::T) -> Result<FAddress>
    where Self::T:std::fmt::Debug{
        let addr = handler.allocate(Self::size()?)?;
        Ok(Self::dump_allocated(handler, addr, data)?)
    }
    fn dump_allocated(handler: &mut FileHandler, addr: FAddress, data: Self::T) -> Result<FAddress>
    where Self::T:std::fmt::Debug{
        log::debug!("Dumping data at address {}: {:?}", addr, data);
        Ok(handler.dump_slice(addr, Self::to_bytes(data)?)?)
    }
    fn delete(handler: &mut FileHandler, addr: FAddress) -> Result<()>{
        log::debug!("Deleting data at address {}", addr);
        handler.delete_range(addr, Self::size()?)?;
        Ok(())
    }
}
impl FileHandle for u64{
    type T = u64;
    fn size() -> Result<u64>{
        Ok(8)
    }
    fn from_bytes(slice: Vec<u8>) -> Result<u64>{
        Ok(u64::from_be_bytes(slice.try_into().unwrap()))
    }
    fn to_bytes(data: u64) -> Result<Vec<u8>>{
        Ok(data.to_be_bytes().to_vec())
    }
}
impl FileHandle for f64{
    type T = f64;
    fn size() -> Result<u64>{
        Ok(8)
    }
    fn from_bytes(slice: Vec<u8>) -> Result<f64>{
        Ok(f64::from_be_bytes(slice.try_into().unwrap()))
    }
    fn to_bytes(data: f64) -> Result<Vec<u8>>{
        Ok(data.to_be_bytes().to_vec())
    }
}
impl FileHandle for f32{
    type T = f32;
    fn size() -> Result<u64>{
        Ok(4)
    }
    fn from_bytes(slice: Vec<u8>) -> Result<f32>{
        Ok(f32::from_be_bytes(slice.try_into().unwrap()))
    }
    fn to_bytes(data: f32) -> Result<Vec<u8>>{
        Ok(data.to_be_bytes().to_vec())
    }
}
impl FileHandle for bool{
    type T = bool;
    fn size() -> Result<u64>{
        Ok(1)
    }
    fn from_bytes(slice: Vec<u8>) -> Result<bool>{
        Ok(slice[0] != 0)
    }
    fn to_bytes(data: bool) -> Result<Vec<u8>>{
        Ok(vec![data as u8])
    }
}
impl FileHandle for char{
    type T = char;
    fn size() -> Result<u64>{
        Ok(1)
    }
    fn from_bytes(slice: Vec<u8>) -> Result<char>{
        Ok(slice[0] as char)
    }
    fn to_bytes(data: char) -> Result<Vec<u8>>{
        Ok(vec![data as u8])
    }
}
impl FileHandle for u8{
    type T = u8;
    fn size() -> Result<u64>{
        Ok(1)
    }
    fn from_bytes(slice: Vec<u8>) -> Result<u8>{
        Ok(slice[0])
    }
    fn to_bytes(data: u8) -> Result<Vec<u8>>{
        Ok(vec![data])
    }
}
impl FileHandle for Vec<u8>{
    type T = Vec<u8>;
    fn size() -> Result<u64>{
        Ok(8)
    }
    fn from_bytes(slice: Vec<u8>) -> Result<Vec<u8>>{
        Ok(slice)
    }
    fn to_bytes(data: Vec<u8>) -> Result<Vec<u8>>{
        Ok(data)
    }
    fn load(handler: &FileHandler, addr: FAddress) -> Result<(FAddress, Self::T)>
    where Self::T:std::fmt::Debug{
        log::debug!("Loading data at address {}", addr);
        let (main_addr, vec_addr) = FAddress::load(handler, addr)?;
        let (vec_addr, vec_size) = u64::load(handler,vec_addr)?;
        let mut data = vec![0;vec_size as usize];
        let mut i = 0;
        let mut addr = vec_addr;
        loop{
            let (next, slice) = handler.load_slice(addr, 256)?;
            for j in 0..256{
                if i>=vec_size{
                    break;
                }
                data[i as usize] = slice[j as usize];
                i += 1;
            }
            log::debug!("Loading slice at {}: {:?}",next,slice);
            let (_next, next_node) = FAddress::load(handler, next)?;
            if next_node == 0{
                return Ok((main_addr, data));
            }
            addr = next_node;
        }
    }
    fn dump_allocated(handler: &mut FileHandler, addr: FAddress, data: Self::T) -> Result<FAddress>
    where Self::T:std::fmt::Debug{
        log::debug!("Dumping data at address {}: {:?}", addr, data);
        let vec_addr = handler.allocate(FAddress::size()?+256+FAddress::size()?)?;
        let main_addr = FAddress::dump_allocated(handler,addr,vec_addr)?;
        let vec_size = data.len();
        let vec_addr = u64::dump_allocated(handler, vec_addr, vec_size as u64)?;
        let mut addr = vec_addr;
        let mut slice = vec![0;256];
        let mut i = 0;
        loop{
            for j in 0..256{
                if i>=vec_size{
                    slice[i] = 0;
                }
                else{
                    slice[j] = data[i];
                    i += 1;
                }
            }
            log::debug!("Dumping slice at {}: {:?}",vec_addr,slice);
            let vec_addr = handler.dump_slice(addr, slice.clone())?;
            let vec_addr = if i>= vec_size{
                FAddress::dump_allocated(handler, vec_addr, 0)?
            }
            else{
                let vec_addr_new = handler.allocate(256+FAddress::size()?)?;
                FAddress::dump_allocated(handler, vec_addr, vec_addr_new)?;
                vec_addr_new
            };
            if i>= vec_size{
                return Ok(main_addr);
            }
            addr = vec_addr;
        }
    }
    fn delete(handler: &mut FileHandler, addr: FAddress) -> Result<()>{
        log::debug!("Deleting data at address {}", addr);
        FAddress::delete(handler, addr)?;
        let (_addr, vec_addr) = FAddress::load(handler, addr)?;
        u64::delete(handler, vec_addr)?;
        let (mut vec_addr, vec_size) = u64::load(handler, vec_addr)?;
        let iterations = ((vec_size)+(256-1))/256;
        for i in 0..iterations{
            handler.delete_range(vec_addr, 256)?;
            let (vec_addr_tmp, _slice) = handler.load_slice(vec_addr, 256)?;
            FAddress::delete(handler, vec_addr_tmp)?;
            let (_vec_addr_tmp, vec_addr_new) = FAddress::load(handler, vec_addr_tmp)?;
            vec_addr = vec_addr_new;
        }
        Ok(())
    }
}
impl FileHandle for String{
    type T = String;
    fn size() -> Result<u64>{
        Ok(8)
    }
    fn from_bytes(slice: Vec<u8>) -> Result<String>{
        Ok(std::str::from_utf8(&slice)?.to_string())
    }
    fn to_bytes(data: String) -> Result<Vec<u8>>{
        Ok(data.as_bytes().to_vec())
    }
    fn load(handler: &FileHandler, addr: FAddress) -> Result<(FAddress, Self::T)>
    where Self::T:std::fmt::Debug{
        let (addr ,slice) = Vec::load(handler, addr)?;
        Ok((addr, Self::from_bytes(slice)?))
    }
    fn dump_allocated(handler: &mut FileHandler, addr: FAddress, data: Self::T) -> Result<FAddress>
    where Self::T:std::fmt::Debug{
        Ok(Vec::dump_allocated(handler, addr, Self::to_bytes(data)?)?)
    }
    fn delete(handler: &mut FileHandler, addr: FAddress) -> Result<()>{
        Vec::delete(handler, addr)?;
        Ok(())
    }
}