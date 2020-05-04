package Communication;

import java.io.*;

public class Message
{
    private Endpoint endpoint;
    private String header;
    private String body;

    public Message()
    {

    }

    public Message(String header, String body)
    {
        this.endpoint = null;
        this.header = header;
        this.body = body;
    }

    public Message(Endpoint endpoint, String header, String body)
    {
        this.endpoint = endpoint;
        this.header = header;
        this.body = body;
    }

    public Endpoint getEndpoint() { return endpoint; }
    public String getHeader() { return header; }
    public String getBody() { return body; }

    public void writeTo(OutputStream stream) throws IOException
    {
        String messageToPrint = header + System.lineSeparator() + body + System.lineSeparator();
        stream.write(messageToPrint.getBytes());
    }

    public void readFrom(InputStream stream) throws IOException
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(stream));
        StringBuilder bufferMessage = new StringBuilder();
        do
        {
            bufferMessage.append(reader.readLine());
            bufferMessage.append(System.lineSeparator());
        } while (reader.ready());
        String[] inputParsed = bufferMessage.toString().split(System.lineSeparator());

        header = inputParsed[0];
        if (inputParsed.length > 1) {
            body = inputParsed[1];
        }
    }

    public String toString(){ return header + ":" + body; }
}
