use serde_json::Value;
use serde::{Deserialize, Serialize};
use crate::Result;

#[derive(Deserialize,Serialize)]
pub struct Request {
    pub process: String,
    pub data: Value
}

#[derive(Serialize)]
pub struct ResponseStatus {
    pub r#type: String,
    pub reason: String
}

#[derive(Serialize)]
pub struct Response {
    pub status: ResponseStatus,
    pub data: Value
}

impl ResponseStatus {
    pub fn ok() -> Result<ResponseStatus> {
        Ok(ResponseStatus{r#type:"OK".to_string(),reason:"Success".to_string()})
    }
    pub fn error(msg: String) -> Result<ResponseStatus> {
        Ok(ResponseStatus{r#type:"ERROR".to_string(),reason:msg})
    }
}

impl Response {
    pub fn ok(data: Value) -> Result<Response>{
        Ok(Response{status:ResponseStatus::ok()?, data:data})
    }
    pub fn error(data: Value, msg: String) -> Result<Response>{
        Ok(Response{status:ResponseStatus::error(msg)?, data:data})
    }
}