use std::collections::HashMap;
use crate::Result;
use crate::database::Table;
use crate::database::Generator;
use crate::database::RowSchema;

pub struct Database{
    tables: HashMap<String, Table>,
    gen: Generator
}

impl Database{
    pub fn new() -> Result<Database>{
        Ok(Database{tables:HashMap::new(),gen:Generator::new(0)?})
    }

    pub fn add_table(&mut self, name: &str, rowschema: RowSchema) -> Result<()>{
        let table = Table::new(name.to_string(), rowschema,  self)?;
        self.tables.insert(name.to_string(), table);

        Ok(())
    }

    pub fn get_table(&mut self, name:&str) -> Result<&mut Table>{
        Ok(self.tables.get_mut(name).unwrap())
    }

    pub fn gen_next(&mut self) -> Result<usize>{
        Ok(self.gen.next()?)
    }
}