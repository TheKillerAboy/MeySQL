#[cfg(test)]
mod database_tests {
    use crate::Result;
    use crate::database::Types;
    use crate::database::Cell;
    use crate::database::Row;
    use crate::database::RowSchema;
    use crate::database::Generator;
    use crate::database::Database;
    use crate::database::Table;

    fn init() {
        let _ = env_logger::builder().is_test(true).try_init();
    }

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

    fn example_row(i: usize) -> Result<Row>{
        let mut cells : Vec<Cell> = vec![];
        match i{
            0 => {
                let mut id = Cell::new()?;
                id.set_int(12)?;

                let mut name = Cell::new()?;
                name.set_string("Annekin")?;

                let mut surname = Cell::new()?;
                surname.set_string("Meyburgh")?;

                cells = vec![id, name, surname];
            }
            _ => {}
        }
        Ok(Row::new(cells)?)
    }

    #[test]
    fn row_tests() -> Result<()>{
        init();

        let mut example_row_1 = example_row(0)?;

        assert_eq!(example_row_1.get_id()?, 0);

        example_row_1.set_id(2223);
        assert_eq!(example_row_1.get_id()?, 2223);

        assert_eq!(example_row_1[0].get_int()?, 12);
        assert_eq!(example_row_1[1].get_string()?, "Annekin");
        assert_eq!(example_row_1[2].get_string()?, "Meyburgh");

        let mut eval = Cell::new()?;

        eval.set_int(12)?;
        assert_eq!(example_row_1[0], eval);
        eval.set_string("Annekin")?;
        assert_eq!(example_row_1[1], eval);
        eval.set_string("Meyburgh")?;
        assert_eq!(example_row_1[2], eval);

        Ok(())
    }

    #[test]
    fn generator_tests() -> Result<()>{
        init();

        let mut gen = Generator::new(12)?;
        assert_eq!(gen.next()?, 12);

        for _ in 1..100{
            gen.next()?;
        }

        assert_eq!(gen.next()?, 112);

        Ok(())
    }

    #[test]
    fn rowschema_tests() -> Result<()>{
        init();

        let rowschema = RowSchema::new(
            vec![Types::INT, Types::STRING, Types::STRING]
        )?;

        assert_eq!(rowschema[0], Types::INT);
        assert_eq!(rowschema[1], Types::STRING);

        Ok(())
    }

    fn example_database(i: usize) -> Result<Database>{
        let mut db = Database::new()?;
        match i{
            0 => {
                let rowschema = RowSchema::new(
                    vec![Types::INT, Types::STRING, Types::STRING]
                )?;
                db.add_table("People", rowschema)?;
            },
            _ => {}
        }

        Ok(db)
    }

    #[test]
    fn database_tests() -> Result<()>{
        init();

        let mut db = example_database(0)?;
        let _table = db.get_table("People")?;

        Ok(())
    }

    #[test]
    fn table_tests() -> Result<()>{
        init();

        let mut db = example_database(0)?;
        let table = db.get_table("People")?;

        assert_eq!(table.get_name()?, "People");

        let row = example_row(0)?;
        table.add_row(row)?;

        Ok(())
    }
}