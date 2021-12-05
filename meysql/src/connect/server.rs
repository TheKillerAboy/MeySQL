use std::net::{TcpListener};
use crate::Result;

pub struct Server{
    listener: TcpListener,
    id_gen: usize
}

impl Server{
    pub fn new(port: u64)->Result<Server>{
        println!("Running on Port: {}", port);
        let server = Server{
            listener:TcpListener::bind(format!("127.0.0.1:{}",port))?,
            id_gen: 1
        };
        Ok(server)
    }

    pub fn run(&mut self, config: serde_yaml::Value)->Result<()>{
        println!("Running Version: {}", config["version"].as_str().unwrap());
        for stream in self.listener.incoming() {
            let mut con = crate::connect::Connection::new(stream?, self.id_gen)?;
            self.id_gen+=1;
            con.run()?;
        }
        Ok(())
    }
}