mod capacity_test;
mod functionality_test;

extern crate clap;

use clap::{App, Arg};
use colored::*;
use std::fs::File;
use std::process::{exit, Child, Command, Stdio};
use std::thread::sleep;
use std::time::Instant;

use functionality_test as ft;

struct Settings {
    host: String,
    port: String,
    type_: String,
    need_server: bool,
    debug: bool,
}

macro_rules! kill_server {
    ($child:expr, $bool:expr) => {
        if let Some(ref mut child) = $child {
            if $bool {
                child.kill().unwrap();
            }
        }
    };
}

pub fn run_server(
    port: i32,
    width: i32,
    height: i32,
    names: Vec<String>,
    clients_nb: i32,
    freq: i32,
    debug: bool,
) -> std::io::Result<Child> {
    let names = names.join(" ");
    let log_file = File::create("./server_test.log")?;

    let mut cmd = Command::new("./zappy_server");
    cmd.arg("-p")
        .arg(port.to_string())
        .arg("-x")
        .arg(width.to_string())
        .arg("-y")
        .arg(height.to_string())
        .arg("-n")
        .arg(names)
        .arg("-c")
        .arg(clients_nb.to_string())
        .arg("-f")
        .arg(freq.to_string())
        .stdout(Stdio::from(log_file.try_clone()?))
        .stderr(Stdio::from(log_file));

    if debug {
        cmd.arg("-d");
    }

    let child = cmd.spawn()?;

    Ok(child)
}

fn parse_option() -> Settings {
    let matches = App::new("Functional Test Zappy")
        .arg(
            Arg::with_name("host")
                .short('h')
                .long("host")
                .value_name("HOST")
                .help("Set the host address, default is localhost")
                .takes_value(true),
        )
        .arg(
            Arg::with_name("port")
                .short('p')
                .long("port")
                .value_name("PORT")
                .help("Set the port number, default is 8080")
                .takes_value(true),
        )
        .arg(
            Arg::with_name("type")
                .short('t')
                .long("type")
                .help("Set the type of test, default is basic, can be basic, capacity or full")
                .takes_value(true),
        )
        .arg(
            Arg::with_name("server")
                .short('s')
                .long("server")
                .help("Set need of run server, default is false"),
        )
        .arg(
            Arg::with_name("debug")
                .short('d')
                .long("debug")
                .help("Set debug mode for server, default is false"),
        )
        .get_matches();

    let host = matches.value_of("host").unwrap_or("localhost").to_string();
    let port = matches.value_of("port").unwrap_or("8080").to_string();
    let type_ = matches.value_of("type").unwrap_or("basic").to_string();
    let need_server = matches.is_present("server");
    let debug = matches.is_present("debug");
    if (port.parse::<i32>().is_err()) || (port.parse::<i32>().unwrap() < 0) {
        println!("{}: Invalid port number", "Error".red());
        exit(1);
    }
    if (type_ != "basic") && (type_ != "capacity") && (type_ != "full") {
        println!("{}: Invalid type of test", "Error".red());
        exit(1);
    }
    Settings {
        host,
        port,
        type_,
        need_server,
        debug,
    }
}

fn launch_server(option: &Settings) -> Option<Child> {
    let mut child: Option<Child>;
    print!("{}: Run server", "Running".yellow());
    match run_server(
        option.port.parse::<i32>().unwrap_or(8080),
        10,
        10,
        vec!["t1".to_string(), "t2".to_string()],
        2,
        100,
        option.debug,
    ) {
        Ok(c) => {
            child = Some(c);
        }
        Err(e) => {
            println!("\r{}: {}: {}", "KO".red(), "Failed to init server".red(), e);
            exit(1);
        }
    }

    if let Some(ref mut child_process) = child {
        match child_process.try_wait() {
            Ok(Some(status)) => {
                println!("\r{}: Server exited with status: {}", "KO".red(), status);
                exit(1);
            }
            Ok(None) => {
                println!("\r{}: {}", "OK".green(), "Server is running".green());
            }
            Err(e) => {
                println!("\r{}: error attempting to wait: {}", "KO".red(), e);
                exit(1);
            }
        }
    }
    child
}

fn main() {
    let option = parse_option();
    let mut child: Option<Child> = if option.need_server {
        launch_server(&option)
    } else {
        None
    };
    sleep(std::time::Duration::from_millis(500));
    let start = Instant::now();
    match ft::basic_test(&option.host, &option.port, &option.type_) {
        Ok(_) => {
            let duration = start.elapsed();
            println!(
                "{}: {} ({:?})",
                "OK".green(),
                "Basic test".green(),
                duration
            );
        }
        Err(_e) => {
            println!("{}: {}", "KO".red(), "Basic test".red());
            kill_server!(child, option.need_server);
            exit(1);
        }
    }
    if (option.type_ == "full") || (option.type_ == "capacity") {
        match capacity_test::test_capacity(&option.host, &option.port) {
            Ok(_) => {
                let duration = start.elapsed();
                println!(
                    "{}: {} ({:?})",
                    "OK".green(),
                    "Capacity test".green(),
                    duration
                );
            }
            Err(e) => {
                println!("{}: {}: {}", "\rKO".red(), "Capacity test".red(), e);
                kill_server!(child, option.need_server);
                exit(1);
            }
        }
    }
    println!(
        "{}: All tests passed in {:?}",
        "OK".green(),
        start.elapsed()
    );
    kill_server!(child, option.need_server);
}
