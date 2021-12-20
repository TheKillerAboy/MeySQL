use crate::database::Types;
use crate::Result;
use std::{fmt,error,ptr};
use core::ffi::c_void;
use std::alloc;

#[derive(Debug)]
pub struct CellTypeError {
    r#type: String
}

impl CellTypeError {
    fn new(msg: &str) -> CellTypeError {
        CellTypeError{r#type: msg.to_string()}
    }
}

impl fmt::Display for CellTypeError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f,"{} is not the type of this cell",self.r#type)
    }
}

impl error::Error for CellTypeError {
    fn description(&self) -> &str {
        &self.r#type
    }
}

#[derive(Debug)]
pub struct Cell{
    layout: Option<alloc::Layout>,
    value: *mut u8,
    len: usize,
    r#type: Types
}

pub trait CellTrait{
    fn cell_name() -> Result<String>;
    fn cell_type() -> Result<Types>;
    fn get_cell_value(cell: &Cell) -> Result<Self>
    where Self: Clone{
        Ok(cell.get_value_prim::<Self>(Self::cell_type()?, &Self::cell_name()?)?)
    }
    fn set_cell_value(cell: &mut Cell, val: Self) -> Result<()>
    where Self: Clone{
        cell.set_value_prim::<Self>(val, Self::cell_type()?)?;
        Ok(())
    }
    fn cell_eq(cellA: &Cell, cellB: &Cell) -> Result<bool>
    where Self: Clone,
          Self: PartialEq{
        if cellA.r#type != cellB.r#type{
            return Ok(false);
        }
        if cellA.r#type != Self::cell_type()?{
            return Err(Box::new(CellTypeError::new(&format!("Equality mixup, using {} for equality", Self::cell_name()?))));
        }
        Ok(Self::get_cell_value(cellA)? == Self::get_cell_value(cellB)?)
    }
}

impl Cell{
    pub fn new() -> Result<Cell> {
        Ok(Cell{layout:None, value:ptr::null_mut(),len:0,r#type:Types::NULL})
    }

    pub fn get_value_prim<T>(&self, t: Types, e: &str) -> std::result::Result<T, CellTypeError>
    where T: Clone{
        if self.r#type != t{
            return Err(CellTypeError::new(e));
        }
        Ok(unsafe{&*(self.value as *mut T)}.clone())
    }
    pub fn get_value<T>(&self) -> Result<T>
    where T: CellTrait,
          T: Clone{
        Ok(T::get_cell_value(self)?)
    }
    pub fn set_null(&mut self) -> Result<()>{
        if self.r#type != Types::NULL{
            unsafe{
                alloc::dealloc(self.value, self.layout.unwrap())
            }
            self.layout = None;
            self.r#type = Types::NULL;
        }
        Ok(())
    }
    pub fn set_value_prim<T>(&mut self, val: T, t: Types) -> Result<()>
    where T: Clone{
        self.set_null()?;
        unsafe{
            self.layout = Some(alloc::Layout::new::<T>());
            self.value = alloc::alloc(self.layout.unwrap());
            *(self.value as *mut T) = val.clone();
        }
        self.r#type = t;
        Ok(())
    }
    pub fn set_value<T>(&mut self, val: T) -> Result<()>
    where T: CellTrait,
          T: Clone{
        T::set_cell_value(self, val)?;
        Ok(())
    }
    pub fn get_type(&self) -> Result<Types>{
        Ok(self.r#type)
    }
    pub fn eq(&self, other: &Cell) -> Result<bool>{
        match self.get_type()?{
            Types::BOOL => return Ok(bool::cell_eq(self, other)?),
            Types::CHAR => return Ok(char::cell_eq(self, other)?),
            Types::INT => return Ok(u64::cell_eq(self, other)?),
            Types::FLOAT => return Ok(f32::cell_eq(self, other)?),
            Types::DOUBLE => return Ok(f64::cell_eq(self, other)?),
            Types::STRING => return Ok(String::cell_eq(self, other)?),
            _ => {}
        }
        Ok(false)
    }
}
impl PartialEq for Cell {
    fn eq(&self, other: &Self) -> bool {
        self.eq(other).unwrap()
    }
}

impl CellTrait for u64{
    
    fn cell_name() -> Result<String>{
        Ok("INT".to_string())
    }
    fn cell_type() -> Result<Types>{
        Ok(Types::INT)
    }
}

impl CellTrait for bool{
    
    fn cell_name() -> Result<String>{
        Ok("BOOL".to_string())
    }
    fn cell_type() -> Result<Types>{
        Ok(Types::BOOL)
    }
}

impl CellTrait for char{
    
    fn cell_name() -> Result<String>{
        Ok("CHAR".to_string())
    }
    fn cell_type() -> Result<Types>{
        Ok(Types::CHAR)
    }
}

impl CellTrait for f32{
    
    fn cell_name() -> Result<String>{
        Ok("FLOAT".to_string())
    }
    fn cell_type() -> Result<Types>{
        Ok(Types::FLOAT)
    }
}

impl CellTrait for f64{
    
    fn cell_name() -> Result<String>{
        Ok("DOUBLE".to_string())
    }
    fn cell_type() -> Result<Types>{
        Ok(Types::DOUBLE)
    }
}

impl CellTrait for String{
    
    fn cell_name() -> Result<String>{
        Ok("STRING".to_string())
    }
    fn cell_type() -> Result<Types>{
        Ok(Types::STRING)
    }
    fn get_cell_value(cell: &Cell) -> Result<String>
    where String: Clone{
        if cell.r#type != Types::STRING{
            return Err(Box::new(CellTypeError::new("String")));
        }
        Ok(unsafe { std::str::from_utf8_unchecked(std::slice::from_raw_parts(cell.value, cell.len)) }.to_string().clone())
    }
    fn set_cell_value(cell: &mut Cell, val: String) -> Result<()>
    where String: Clone{
        cell.set_null()?;
        unsafe{
            cell.len = val.len();
            cell.layout = Some(alloc::Layout::from_size_align(cell.len, std::mem::align_of::<u8>())?);
            cell.value = alloc::alloc(cell.layout.unwrap());
            ptr::copy_nonoverlapping(val.clone().as_ptr(), cell.value, cell.len);
        }
        cell.r#type = Types::STRING;
        Ok(())
    }
}