#[cfg(test)]
mod connect_tests {
    use serde_json::json;

    use crate::connect::Server;
    use crate::connect::Client;
    use crate::read_config;
    use crate::Result;
    use std::thread;

    fn init() {
        let _ = env_logger::builder().is_test(true).try_init();
    }
    #[test]
    fn basic_connect_test() -> Result<()>{
        let port = 3359;

        init();
        
        let config = read_config()?;
        
        let server = thread::spawn(move ||{
            let mut server = Server::new(port).unwrap();
            server.run(config, Some(1)).unwrap();
        });
        let mut client = Client::new("127.0.0.1".to_string(), port)?;
        client.run(json!({"process":"system-info", "data":{}}).to_string())?;
        drop(client);
        server.join().unwrap();
        Ok(())
    }

    #[test]
    fn expire_server_test() -> Result<()>{
        let port = 33522;

        init();

        let expire = 5;

        let config = read_config()?;
        
        let server = thread::spawn(move ||{
            let mut server = Server::new(port).unwrap();
            server.run(config, Some(expire)).unwrap();
        });
        for i in 0..expire{
            log::info!("Iteration: {}", i);
            let mut client = Client::new("127.0.0.1".to_string(), port)?;
            client.run(json!({"process":"system-info", "data":{}}).to_string())?;
            drop(client);
        }
        server.join().unwrap();

        Ok(())
    }
}