use std::io::{Read, Write};
use std::net::TcpStream;

pub struct Client {
    stream: TcpStream,
}

impl Client {
    pub fn new(host: &str, port: &str) -> Result<Client, std::io::Error> {
        let stream = TcpStream::connect(format!("{}:{}", host, port))?;
        Ok(Client { stream })
    }

    pub fn verification_still_connect(&mut self) -> std::io::Result<()> {
        let mut buffer = [0; 1024];
        self.stream.write(b"GRAPHIC\n")?;self.stream
            .set_read_timeout(Some(std::time::Duration::from_secs(5)))?;
        self.stream.read(&mut buffer)?;
        if (String::from_utf8_lossy(&buffer)).is_empty() {
            return Err(std::io::Error::new(
                std::io::ErrorKind::Other,
                "Server does not respond",
            ));
        }
        Ok(())
    }

    pub fn send_big_message(&mut self) -> std::io::Result<()> {
        let mut buffer = [0; 131072];
        for i in 0..131072 {
            buffer[i] = 42;
        }
        self.stream.write(&buffer)?;
        self.stream
            .set_read_timeout(Some(std::time::Duration::from_secs(5)))?;
        match self.stream.read(&mut buffer) {
            Ok(_) => {}
            Err(e) => {
                if e.kind() == std::io::ErrorKind::TimedOut {
                    println!("timeout");
                    return Ok(());
                }
            }
        }
        if (String::from_utf8_lossy(&buffer)).is_empty() {
            return Err(std::io::Error::new(
                std::io::ErrorKind::Other,
                "Server does not respond",
            ));
        }
        Ok(())
    }
}
