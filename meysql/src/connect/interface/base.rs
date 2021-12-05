use crate::Result;
use crate::connect::interface::types::{Request,Response};

pub trait Interface{
    fn name() -> Result<String>;
    fn method(req: Request) -> Result<Response>;
}