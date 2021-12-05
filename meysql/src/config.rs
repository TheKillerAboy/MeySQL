use serde_yaml::Value;
use crate::Result;

pub fn read_config() -> Result<Value> {
    let mut cfg_path = project_root::get_project_root()?;
    cfg_path.push("config.yaml");
    log::debug!("Config Path: {:?}", cfg_path);
    let f = std::fs::File::open(cfg_path)?;
    Ok(serde_yaml::from_reader(f)?)
}