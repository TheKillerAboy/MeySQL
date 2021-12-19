#[cfg(test)]
mod filehandlers_tests {
    use crate::Result;
    use std::fs::File;
    use crate::database::filehandlers::{FileHandler, FileHandle};
    
    fn init() {
        let _ = env_logger::builder().is_test(true).try_init();
    }
    
    #[test]
    fn file_handler_prim_test() -> Result<()>{
        init();
        {
            File::create("tests_tmp/file_handler_test.db")?;
        }
        let mut file = FileHandler::open("tests_tmp/file_handler_test.db")?;

        let addr = u64::dump(&mut file, 33)?;
        let (_addr, val) = u64::load(&file, addr-u64::size()?)?;
        assert_eq!(val, 33);

        let v: f32 = 33.21;
        let addr = f32::dump(&mut file, v)?;
        let (_addr, val) = f32::load(&file, addr-f32::size()?)?;
        assert_eq!(val, v);

        let v: f64 = 33.21;
        let addr = f64::dump(&mut file, v)?;
        let (_addr, val) = f64::load(&file, addr-f64::size()?)?;
        assert_eq!(val, v);

        let addr = u64::dump(&mut file, 33)?;
        let (_addr, val) = u64::load(&file, addr-u64::size()?)?;
        assert_eq!(val, 33);

        let addr = bool::dump(&mut file, true)?;
        let (_addr, val) = bool::load(&file, addr-bool::size()?)?;
        assert_eq!(val, true);

        let addr = char::dump(&mut file, 'c')?;
        let (_addr, val) = char::load(&file, addr-char::size()?)?;
        assert_eq!(val, 'c');

        let addr = Vec::dump(&mut file, vec![1,2,3,4,5,6])?;
        let (_addr, val) = Vec::load(&file, addr-Vec::size()?)?;
        assert_eq!(val, vec![1,2,3,4,5,6]);

        let addr = String::dump(&mut file, "Hello Daar".to_string())?;
        let (_addr, val) = String::load(&file, addr-String::size()?)?;
        assert_eq!(val, "Hello Daar".to_string());

        Ok(())
    }
    #[test]
    fn file_handle_to_bytes_test() -> Result<()>{
        init();

        let slice = u64::to_bytes(33)?;
        assert_eq!(slice, vec![0,0,0,0,0,0,0,33]);

        let slice = u64::to_bytes(257)?;
        assert_eq!(slice, vec![0,0,0,0,0,0,1,1]);

        //Add tests for float

        let slice = bool::to_bytes(true)?;
        assert_eq!(slice, vec![1]);

        let slice = char::to_bytes('c')?;
        assert_eq!(slice, vec![99]);

        Ok(())
    }
    #[test]
    fn file_handle_from_bytes_test() -> Result<()>{
        init();

        let val = u64::from_bytes(vec![0,0,0,0,0,0,0,33])?;
        assert_eq!(val, 33);

        let val = u64::from_bytes(vec![0,0,0,0,0,0,1,1])?;
        assert_eq!(val, 257);

        //Add tests for float

        let val = bool::from_bytes(vec![1])?;
        assert_eq!(val, true);

        let val = char::from_bytes(vec![99])?;
        assert_eq!(val, 'c');

        Ok(())
    }

    #[test]
    fn file_handler_data_handle_test() -> Result<()>{
        init();

        {
            File::create("tests_tmp/file_handler_data_handle_test.db")?;
        }
        {
            let mut file = FileHandler::open("tests_tmp/file_handler_data_handle_test.db")?;
            u64::dump(&mut file, 200)?;
            u64::dump(&mut file, 4000)?;
            String::dump(&mut file, "500 cheese sticks".to_string())?;
            file.close()?;
        }
        {
            let file = FileHandler::open("tests_tmp/file_handler_data_handle_test.db")?;
            let addr = FileHandler::front()?;
            let (addr, val) = u64::load(&file, addr)?;
            assert_eq!(val, 200);
            let (addr, val) = u64::load(&file, addr)?;
            assert_eq!(val, 4000);
            let (_addr, val) = String::load(&file, addr)?;
            assert_eq!(val, "500 cheese sticks");
        }
        

        Ok(())
    }

    #[test]
    fn file_handler_delete_test() -> Result<()>{
        init();
        {
            {
                File::create("tests_tmp/file_handler_delete_test.db")?;
            }
            let mut file = FileHandler::open("tests_tmp/file_handler_delete_test.db")?;
            u64::dump(&mut file, 200)?;
            u64::dump(&mut file, 4000)?;
            let addr = String::dump(&mut file, "500 cheese sticks".to_string())?;
            u64::dump(&mut file, 300)?;
            String::dump(&mut file, "Hello daar".to_string())?;
            String::delete(&mut file, addr-String::size()?)?;
            log::debug!("Delete Queue {:?} {:?}", file.queue_l, file.queue_r);
            assert_eq!(file.queue_l.len(), 1);
            assert_eq!(file.queue_r.len(), 1);
            file.close()?;
        }
        {
            let file = FileHandler::open("tests_tmp/file_handler_delete_test.db")?;
            log::debug!("Delete Queue {:?} {:?}", file.queue_l, file.queue_r);
            assert_eq!(file.queue_l.len(), 1);
            assert_eq!(file.queue_r.len(), 1);
        }
        {
            {
                File::create("tests_tmp/file_handler_delete_test1.db")?;
            }
            let mut file = FileHandler::open("tests_tmp/file_handler_delete_test1.db")?;
            u64::dump(&mut file, 200)?;
            let addr = u64::dump(&mut file, 4000)?;
            String::dump(&mut file, "500 cheese sticks".to_string())?;
            u64::dump(&mut file, 300)?;
            String::dump(&mut file, "Hello daar".to_string())?;
            u64::delete(&mut file, addr-u64::size()?)?;
            log::debug!("Delete Queue {:?} {:?}", file.queue_l, file.queue_r);
            assert_eq!(file.queue_l.len(), 1);
            assert_eq!(file.queue_r.len(), 1);
            file.close()?;
        }
        {
            let file = FileHandler::open("tests_tmp/file_handler_delete_test1.db")?;
            log::debug!("Delete Queue {:?} {:?}", file.queue_l, file.queue_r);
            assert_eq!(file.queue_l.len(), 1);
            assert_eq!(file.queue_r.len(), 1);
        }
        Ok(())
    }
}