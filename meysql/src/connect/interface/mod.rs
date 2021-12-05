pub mod types;
pub mod system_info;
pub mod base;
use crate::Result;
use types::{Request, Response};
use system_info::SystemInfo;
use crate::connect::interface::base::Interface;
use serde_json::json;

pub fn process(req: Request) -> Result<Response>{
    if req.process == SystemInfo::name()? {
        return Ok(SystemInfo::method(req)?);
    }
    
    Ok(Response::error(json!({}), "No Process match".to_string())?)
}