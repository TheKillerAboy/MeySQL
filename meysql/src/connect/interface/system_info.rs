use crate::connect::interface::base::Interface;
use crate::connect::interface::types::{Request,Response};
use serde_json::json;
use crate::Result;
use crate::read_config;

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