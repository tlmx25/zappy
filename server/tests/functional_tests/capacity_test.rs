mod client;

use colored::Colorize;
use std::io::{Result, Write};
use std::thread;

fn max_client(nbr_client: i32, host: &str, port: &str) -> Result<()> {
    let mut handles = vec![];
    print!("{}: Handle Clients", "Running".yellow());
    std::io::stdout().flush().unwrap();
    for tmp in 0..nbr_client {
        let host = host.to_string();
        let port = port.to_string();
        let handle = thread::spawn(move || {
            let mut client = client::Client::new(&host, &port).unwrap();
            match client.verification_still_connect() {
                Ok(_) => {
                    print!(
                        "\r{}: Handle Clients {}/{}",
                        "Running".yellow(),
                        tmp,
                        nbr_client
                    );
                    std::io::stdout().flush().unwrap();
                }
                Err(e) => {
                    return Err(e);
                }
            }
            Ok(())
        });
        handles.push(handle);
    }
    for handle in handles {
        match handle.join() {
            Ok(_) => {}
            Err(_e) => {
                println!("{}: Capacity failed", "KO".red());
            }
        }
    }
    println!(
        "\r{}: Handle multiple client : {} clients",
        "OK".green(),
        nbr_client
    );
    Ok(())
}

pub fn test_capacity(host: &str, port: &str) -> Result<()> {
    for &client_count in &[50, 100, 150] {
        match max_client(client_count, host, port) {
            Ok(_) => {}
            Err(_e) => {
                return Err(std::io::Error::new(
                    std::io::ErrorKind::Other,
                    "Max client failed",
                ));
            }
        }
    }
    Ok(())
}
