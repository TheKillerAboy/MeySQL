use crate::Result;
use crate::read_config;
use std::net::TcpStream;

pub struct Client{
    stream: TcpStream
}

impl Client{
    pub fn new(host: String) -> Result<Client> {
        let config = read_config()?;
        let fullhost = format!("{}:{}", host, config["test"]["port"].as_u64().unwrap());
        log::info!("Running: {}", fullhost);
        Ok(Client{stream:TcpStream::connect(fullhost)?})
    }
}