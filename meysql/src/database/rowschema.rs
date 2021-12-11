use crate::database::Types;
use crate::Result;
use std::ops::Index;

pub struct RowSchema{
    pub cells: Vec<Types>
}

impl RowSchema{
    pub fn new(cells: Vec<Types>) -> Result<RowSchema>{
        Ok(RowSchema{cells:cells})
    }

    pub fn get(&self, i: usize) -> Result<&Types>{
        Ok(&self.cells[i])
    }
}

impl Index<usize> for RowSchema {
    type Output = Types;
    fn index<'a>(&'a self, i: usize) -> &'a Types {
        match self.get(i){
            Ok(c) => return c,
            Err(e) => panic!("{:?}", e)
        }
    }
}