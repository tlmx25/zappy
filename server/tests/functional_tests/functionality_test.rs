use crate::ft;
use colored::Colorize;

mod basic;

fn test_connect(host: &str, port: &str) -> std::io::Result<()> {
    basic::test_connect_to_server(host, port)
}

fn test_communication(host: &str, port: &str) -> std::io::Result<()> {
    basic::test_first_communication_with_server(host, port)
}

pub fn basic_test(host: &str, port: &str, type_: &str) -> Result<(), std::io::Error> {
    let tests: &[(&str, fn(&str, &str) -> std::io::Result<()>)] =
        if type_ == "basic" || type_ == "full" {
            &[
                ("Connect to server", ft::test_connect),
                ("Communication with server", ft::test_communication),
            ]
        } else {
            &[]
        };
    for (_, (test_name, test)) in tests.iter().enumerate() {
        match test(host, port) {
            Ok(_) => println!("{}: {}", "OK".green(), test_name),
            Err(e) => {
                println!("{}: {} : {}", "KO".red(), test_name, e);
                return Err(std::io::Error::new(
                    std::io::ErrorKind::Other,
                    format!("{} : {}", test_name, e),
                ));
            }
        }
    }
    Ok(())
}
