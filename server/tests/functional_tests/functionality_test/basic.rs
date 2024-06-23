use std::io::Read;
use std::io::Write;
use std::net::TcpStream;

pub fn test_connect_to_server(host: &str, port: &str) -> std::io::Result<()> {
    let _stream = TcpStream::connect(format!("{}:{}", host, port))?;
    Ok(())
}

pub fn test_first_communication_with_server(host: &str, port: &str) -> std::io::Result<()> {
    let mut stream = TcpStream::connect(format!("{}:{}", host, port))?;
    stream.write_all(b"\n")?;

    let mut buffer = [0; 1024];
    stream.read(&mut buffer)?;

    let response = String::from_utf8_lossy(&buffer);
    if response.contains("WELCOME") {
        stream.write_all(b"GRAPHIC\n")?;
        buffer = [0; 1024];
        stream.read(&mut buffer)?;
        if (String::from_utf8_lossy(&buffer)).is_empty() {
            return Err(std::io::Error::new(
                std::io::ErrorKind::Other,
                "Server does not respond",
            ));
        }
        Ok(())
    } else {
        Err(std::io::Error::new(
            std::io::ErrorKind::Other,
            "Server response is not WELCOME",
        ))
    }
}
