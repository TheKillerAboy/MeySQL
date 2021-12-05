#[cfg(test)]
mod connect_tests {
    use crate::connect::Server;
    use crate::connect::Client;
    use crate::read_config;
    use crate::Result;
    #[test]
    fn basic_connect_test() -> Result<()>{
        env_logger::init();
        
        let config = read_config()?;
        let port = config["test"]["port"].as_u64().unwrap();
        let server = Server::new(port);
        let client = Client::new("127.0.0.1".to_string());

        Ok(())
    }
}