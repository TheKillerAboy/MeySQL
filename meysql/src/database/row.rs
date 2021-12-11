use crate::database::Cell;
use crate::Result;
use std::ops::Index;

pub struct Row{
    cells: Vec<Cell>,
    id: usize
}

impl Row{
    pub fn new(cells:Vec<Cell>) -> Result<Row>{
        Ok(Row{cells:cells, id:0})
    }

    pub fn get(&self, i: usize) -> Result<&Cell>{
        Ok(&self.cells[i])
    }

    pub fn set_id(&mut self, id:usize) -> Result<()>{
        self.id = id;

        Ok(())
    }

    pub fn get_id(& self) -> Result<usize>{
        Ok(self.id)
    }
}

impl Index<usize> for Row {
    type Output = Cell;
    fn index<'a>(&'a self, i: usize) -> &'a Cell {
        match self.get(i){
            Ok(c) => return c,
            Err(e) => panic!("{:?}", e)
        }
    }
}