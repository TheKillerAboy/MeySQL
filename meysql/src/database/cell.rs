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

pub struct Cell{
    layout: Option<alloc::Layout>,
    value: *mut u8,
    len: usize,
    r#type: Types
}

impl Cell{
    pub fn new() -> Result<Cell> {
        Ok(Cell{layout:None, value:ptr::null_mut(),len:0,r#type:Types::NULL})
    }

    pub fn get_value<T: Copy>(&self, t: Types, e: &str) -> std::result::Result<T, CellTypeError>{
        if self.r#type != t{
            return Err(CellTypeError::new(e));
        }
        Ok(unsafe{*(self.value as *const T)})
    }

    pub fn get_bool(&self) -> std::result::Result<bool, CellTypeError>{
        Ok(self.get_value(Types::BOOL, "Bool")?)
    }
    pub fn get_char(&self) -> std::result::Result<char, CellTypeError>{
        Ok(self.get_value(Types::CHAR, "Char")?)
    }
    pub fn get_int(&self) -> std::result::Result<u64, CellTypeError>{
        Ok(self.get_value(Types::INT, "Int")?)
    }
    pub fn get_float(&self) -> std::result::Result<f32, CellTypeError>{
        Ok(self.get_value(Types::FLOAT, "Float")?)
    }
    pub fn get_double(&self) -> std::result::Result<f64, CellTypeError>{
        Ok(self.get_value(Types::DOUBLE, "Double")?)
    }
    pub fn get_string(&self) -> std::result::Result<&str, CellTypeError>{
        if self.r#type != Types::STRING{
            return Err(CellTypeError::new("String"));
        }
        Ok(unsafe { std::str::from_utf8_unchecked(std::slice::from_raw_parts(self.value, self.len)) })
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
    pub fn set_value<T>(&mut self, val: T, t: Types) -> Result<()>{
        self.set_null()?;
        unsafe{
            self.layout = Some(alloc::Layout::new::<T>());
            self.value = alloc::alloc(self.layout.unwrap());
            *(self.value as *mut T) = val;
        }
        self.r#type = t;
        Ok(())
    }
    pub fn set_bool(&mut self, val: bool) -> Result<()>{
        self.set_value(val, Types::BOOL)?;
        Ok(())
    }
    pub fn set_char(&mut self, val: char) -> Result<()>{
        self.set_value(val, Types::CHAR)?;
        Ok(())
    }
    pub fn set_int(&mut self, val: u64) -> Result<()>{
        self.set_value(val, Types::INT)?;
        Ok(())
    }
    pub fn set_float(&mut self, val: f32) -> Result<()>{
        self.set_value(val, Types::FLOAT)?;
        Ok(())
    }
    pub fn set_double(&mut self, val: f64) -> Result<()>{
        self.set_value(val, Types::DOUBLE)?;
        Ok(())
    }
    pub fn set_string(&mut self, val: &str) -> Result<()>{
        self.set_null()?;
        unsafe{
            self.len = val.len();
            self.layout = Some(alloc::Layout::from_size_align(self.len, std::mem::align_of::<u8>())?);
            self.value = alloc::alloc(self.layout.unwrap());
            ptr::copy_nonoverlapping(val.as_ptr(), self.value, self.len);
        }
        self.r#type = Types::STRING;
        Ok(())
    }

    pub fn get_type(& self) -> Result<Types>{
        Ok(self.r#type)
    }
}