use serde_json::json;

use crate::Result;
use std::io::{Read,Write};
use std::net::{TcpStream};
use std::str::from_utf8;
use std::time::Duration;
use crate::connect::interface::types::Response;

pub struct Client{
    stream: TcpStream
}

pub static TIMEOUT: Duration = Duration::from_secs(5);

impl Client{
    pub fn new(host: String, port:u64) -> Result<Client> {
        let fullhost = format!("{}:{}", host, port);
        log::info!("Running: {}", fullhost);
        Ok(Client{stream:TcpStream::connect_timeout(&fullhost.parse()?, TIMEOUT)?})
    }

    pub fn run(&mut self,mut payload: String) -> Result<()> {
        log::info!("Sending: {}", payload);
        payload += "\n";
        let buf = payload.as_bytes();
        self.stream.write(&buf)?;
        let mut buf_res = [0 as u8; 1024];
        self.stream.read(&mut buf_res)?;
        let buf_str = from_utf8(&buf_res)?;
        let buf_str = buf_str.trim_matches(char::from(0));
        let res: Response = serde_json::from_str(&buf_str)?;
        log::info!("Recieved: {}",json!(res).to_string());
        if res.status.r#type != "OK" {
            panic!("Not a OK response")
        }
        Ok(())
    }
}