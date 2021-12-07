#[cfg(test)]
mod interface_tests {
    macro_rules! assert_is_type {
        ($t:ty, $i:ident: $ti:ty) => {
            const _: () = {
                fn dummy(v: $t) {
                    let _: $ti = v.$i;
                }
            };
        }
    }

    use serde_json::{Value, from_value};
        use serde_json::json;

    use crate::connect::interface::system_info::SystemInfo;
    use crate::connect::interface::base::Interface;
    use crate::connect::interface::types::{Request, Response};
    use crate::connect::interface::types::ResponseStatus;
    use crate::read_config;
    use crate::Result;

    fn init() {
        let _ = env_logger::builder().is_test(true).try_init();
    }
    #[test]
    fn system_info_test() -> Result<()>{
        init();

        let config = read_config()?;
        assert_eq!(SystemInfo::name()?, "system-info");
        let req: Request = from_value(json!({"process":"","data":{}}))?;
        let res = SystemInfo::method(req)?;
        assert_eq!(json!(res.data),json!(config)); 
        assert_eq!(json!(res.status.r#type),"OK"); 
        Ok(())
    }

    #[test]
    fn types_test() -> Result<()> {
        init();

        let ok = ResponseStatus::ok()?;
        assert_eq!(ok.r#type,"OK");
        assert_eq!(ok.reason,"Success");

        let error_msg = "123";
        let error = ResponseStatus::error(error_msg.to_string())?;
        assert_eq!(error.r#type,"ERROR");
        assert_eq!(error.reason,error_msg);

        assert_is_type!(Request, process: String);
        assert_is_type!(Request, data: Value);
        
        assert_is_type!(ResponseStatus, r#type: String);
        assert_is_type!(ResponseStatus, reason: String);

        assert_is_type!(Response, status: ResponseStatus);
        assert_is_type!(Response, data: Value);

        Ok(())
    }
}