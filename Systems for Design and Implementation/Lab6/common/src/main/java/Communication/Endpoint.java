package Communication;

public class Endpoint
{
    private String host;
    private String port;

    public Endpoint(String host, String port)
    {
        this.host = host;
        this.port = port;
    }

    public String getHost() { return host; }
    public String getPort() { return port; }
    public void setHost(String host) { this.host = host; }
    public void setPort(String port) { this.port = port; }
}
