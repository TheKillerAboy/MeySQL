use crate::meysql::Result;
use crate::meysql::connect::interface::types::{Request,Response};

pub trait Interface{
    fn name() -> Result<String>;
    fn method(req: Request) -> Result<Response>;
}