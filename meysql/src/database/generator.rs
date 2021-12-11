use crate::Result;

pub struct Generator{
    cur: usize
}

impl Generator{
    pub fn new(start: usize) -> Result<Generator>{
        Ok(Generator{cur:start})
    }

    pub fn next(&mut self) -> Result<usize>{
        self.cur += 1;
        Ok(self.cur-1)
    }
}