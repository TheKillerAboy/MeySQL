mod meysql;
use meysql::Result;

fn main() -> Result<()>{
    let mut server = meysql::connect::Server::new()?;
    server.run()?;

    Ok(())
} 