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

    use std::collections::HashSet;
    use std::os::unix::prelude::MetadataExt;

    use serde_json::{Value, from_value};
        use serde_json::json;

    use crate::connect::interface::process;
    use crate::connect::interface::base::Interface;
    use crate::connect::interface;
    use crate::connect::interface::types::{Response, Request};
    use crate::connect::interface::types::ResponseStatus;
    use crate::read_config;
    use crate::Result;

    fn init() {
        let _ = env_logger::builder().is_test(true).try_init();
    }

    #[test]
    fn system_info_test() -> Result<()>{
        init();

        //test process response
        let req: Request = from_value(json!({"process":"system-info","data":{}}))?;
        let res = process(req)?;
        assert_eq!(json!(res.status.r#type), "OK");

        //test interface response
        assert_eq!(interface::SystemInfo::name()?, "system-info");
        let req: Request = from_value(json!({"process":"system-info","data":{}}))?;
        let config = read_config()?;
        let res = interface::SystemInfo::method(req)?;
        assert_eq!(json!(res.status.r#type),"OK"); 
        assert_eq!(json!(res.data),json!(config)); 
        Ok(())
    }

    #[test]
    #[ignore]
    fn sql_query_test() -> Result<()>{
        init();

        // let db = Database("db/test.db");

        // //test process response
        // let req: Request = from_value(json!({"process":"sql-query","data":{"statement":"FROM table SELECT *"}}))?;
        // let res = process(req)?;
        // assert_eq!(json!(res.status.r#type), "OK");

        // //test interface response
        // assert_eq!(interface::SQLQuery::name()?, "table");
        // //test list sub-process
        // let req: Request = from_value(json!({"process":"sql-query","data":{"statement":"FROM table SELECT *"}}))?;
        // let res = interface::SQLQuery::method(req)?;
        // let qres = db.query(req.data["statement"].to_string())
        // assert_eq!(qres, res);
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