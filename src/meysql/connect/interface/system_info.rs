use crate::meysql::connect::interface::base::Interface;
use crate::meysql::connect::interface::types::{Request,Response};
use serde_json::json;
use crate::meysql::Result;
use crate::meysql::read_config;

pub struct SystemInfo{}

impl Interface for SystemInfo{
    fn name() -> Result<String>{
        Ok("system-info".to_string())
    }
    fn method(_req: Request) -> Result<Response>{
        let config = read_config()?;
        Ok(Response::ok(json!(config))?)
    }
}