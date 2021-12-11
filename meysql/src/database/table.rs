use std::collections::LinkedList;
use crate::Result;
use crate::database::Row;
use crate::database::RowSchema;
use crate::database::Database;

pub struct Table{
    rowschema: RowSchema,
    rows: LinkedList<Row>,
    name: String,
    database: *mut Database
}

impl Table{
    pub fn new(name: String, rowschema: RowSchema, database: &mut Database) -> Result<Table> {
        Ok(Table{rowschema:rowschema,rows:LinkedList::new(), name:name, database:database})
    }

    pub fn add_row(&mut self, mut row: Row) -> Result<()>{
        unsafe{
            row.set_id(self.database.as_mut().unwrap().gen_next()?)?;
            self.rows.push_back(row);
        }

        Ok(())
    }

    pub fn get_name(& self) -> Result<String>{
        Ok(self.name.clone())
    }
}