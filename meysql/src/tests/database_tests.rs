#[cfg(test)]
mod database_tests {
    use crate::Result;
    use crate::database::Types;
    use crate::database::Cell;

    fn init() {
        let _ = env_logger::builder().is_test(true).try_init();
    }

    // #[test]
    // #[ignore]
    // fn row_schema_test() -> Result<()>{
    //     let row_schema_test

    //     Ok(())
    // }

    // #[test]
    // #[ignore]
    // fn row_test() -> Result<()>{

    //     Ok(())
    // }

    // #[test]
    // #[ignore]
    // fn table_test() -> Result<()> {
    //     let table_name = "test-table";
    //     let table = Table::new(table_name.to_string());
    //     assert_eq!(table.get_name(), table_name);

    //     Ok(())
    // }

    #[test]
    fn cell_test() -> Result<()>{
        init();
        let mut cell = Cell::new()?;
        assert_eq!(cell.get_type()?, Types::NULL);

        cell.set_bool(true)?;
        assert_eq!(cell.get_bool()?, true);
        assert_eq!(cell.get_type()?, Types::BOOL);

        cell.set_char('c')?;
        assert_eq!(cell.get_char()?, 'c');
        assert_eq!(cell.get_type()?, Types::CHAR);

        cell.set_int(1234)?;
        assert_eq!(cell.get_int()?, 1234);
        assert_eq!(cell.get_type()?, Types::INT);

        cell.set_float(1.5)?;
        assert_eq!(cell.get_float()?, 1.5);
        assert_eq!(cell.get_type()?, Types::FLOAT);

        cell.set_double(1.55)?;
        assert_eq!(cell.get_double()?, 1.55);
        assert_eq!(cell.get_type()?, Types::DOUBLE);

        cell.set_string("hello daar")?;
        assert_eq!(cell.get_string()?, "hello daar");
        assert_eq!(cell.get_type()?, Types::STRING);

        cell.set_null()?;
        assert_eq!(cell.get_type()?, Types::NULL);

        Ok(())
    }
}