use std::net::{TcpListener};
use crate::meysql::Result;

pub struct Server{
    listener: TcpListener,
    id_gen: usize
}

impl Server{
    pub fn new()->Result<Server>{
        let server = Server{
            listener:TcpListener::bind("127.0.0.1:3333")?,
            id_gen: 0
        };
        Ok(server)
    }

    pub fn run(&mut self)->Result<()>{
        for stream in self.listener.incoming() {
            let mut con = crate::meysql::connect::Connection::new(stream?, self.id_gen)?;
            self.id_gen+=1;
            con.run()?;
        }
        Ok(())
    }
}