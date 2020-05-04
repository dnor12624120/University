package Client;

import Communication.Endpoint;
import Communication.Message;
import Domain.Validators.CommunicationException;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class TcpClient
{
    private Endpoint serverEndpoint;

    public TcpClient(Endpoint serverEndpoint)
    {
        this.serverEndpoint = serverEndpoint;
    }

    public Endpoint getServerEndpoint() { return serverEndpoint; }

    public Message sendAndReceive(Message request) throws CommunicationException
    {
        try (Socket socket = new Socket(serverEndpoint.getHost(), Integer.parseInt(serverEndpoint.getPort())))
        {
            try (InputStream inputStream = socket.getInputStream())
            {
                try (OutputStream outputStream = socket.getOutputStream())
                {
                    request.writeTo(outputStream);
                    Message response = new Message();
                    response.readFrom(inputStream);
                    return response;
                }
            }
        }
        catch (IOException e)
        {
            throw new CommunicationException("Error connecting to the server " + e.getMessage());
        }
    }
}
