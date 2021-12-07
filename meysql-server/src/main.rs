use meysql::Result;
use meysql::read_config;

fn main() -> Result<()>{
    env_logger::init();
    
    let config = read_config()?;
    let mut server = meysql::connect::Server::new(config["port"].as_u64().unwrap())?;
    server.run(config, None)?;

    Ok(())
} 