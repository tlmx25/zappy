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
        self.stream.write(b"GRAPHIC\n")?;
        self.stream.read(&mut buffer)?;
        if (String::from_utf8_lossy(&buffer)).is_empty() {
            return Err(std::io::Error::new(
                std::io::ErrorKind::Other,
                "Server does not respond",
            ));
        }
        Ok(())
    }
}
