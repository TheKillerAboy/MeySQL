pub mod connect;
pub mod error;
pub mod config;
pub mod database;
pub use error::Result;
pub use config::read_config;

mod tests;