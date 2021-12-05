use serde_yaml::Value;
use crate::Result;

pub fn read_config() -> Result<Value> {
    let f = std::fs::File::open("config.yaml")?;
    Ok(serde_yaml::from_reader(f)?)
}