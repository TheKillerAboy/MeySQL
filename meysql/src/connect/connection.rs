use std::net::TcpStream;
use crate::Result;
use crate::connect::interface::types::{Request,Response};
use crate::connect::interface::process;
use serde_json::json;
use std::io::{BufRead,BufReader,Write};

pub struct Connection {
    stream: TcpStream,
    id: usize,
}

impl Connection {
    pub fn new(stream: TcpStream, id: usize) -> Result<Connection> {
        Ok(Connection{stream: stream, id:id})
    }

    fn read_req(&mut self) -> Result<Request> {
        let mut buf = String::with_capacity(1024);
        let mut reader = BufReader::new(self.stream.try_clone()?);
        reader.read_line(&mut buf)?;
        let req: Request = serde_json::from_str(& buf)?;
        println!("{} <Recieved {}>", self, json!(req));
        Ok(req)
    }

    fn send_res(&mut self, res : Response) -> Result<()> {
        println!("{} <Sending: {}>", self, json!(res));
        let res_str = serde_json::to_string(&res)?;
        self.stream.write(&res_str.as_bytes())?;
        Ok(())
    }

    pub fn run(&mut self) -> Result<()> {
        let req = self.read_req()?;
        let res = process(req)?;
        self.send_res(res)?;
        Ok(())
    }
}

impl std::fmt::Display for Connection {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "<Connection id={}>", self.id)
    }
}