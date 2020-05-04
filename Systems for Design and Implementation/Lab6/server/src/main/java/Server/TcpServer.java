package Server;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.function.UnaryOperator;
import Communication.Message;

public class TcpServer
{
    private final ExecutorService executorService;
    private final Map<String, UnaryOperator<Message>> methodHandlers;
    private final String port;

    public TcpServer(ExecutorService executorService, String port)
    {
        this.methodHandlers = new HashMap<>();
        this.executorService = executorService;
        this.port = port;
    }

    public void addHandler(String methodName, UnaryOperator<Message> handler)
    {
        methodHandlers.put(methodName, handler);
    }

    public void startServer()
    {
        try (ServerSocket serverSocket = new ServerSocket(Integer.parseInt(port)))
        {
            while (true)
            {
                Socket clientConnection = serverSocket.accept();
                executorService.submit(new ClientHandler(clientConnection));
            }
        }
        catch (IOException e)
        {
            System.out.println(e.getMessage());
        }
    }

    private class ClientHandler implements Runnable
    {
        private final Socket clientSocket;

        public ClientHandler(Socket clientSocket) {
            this.clientSocket = clientSocket;
        }

        @Override
        public void run()
        {
            try (InputStream inputStream = clientSocket.getInputStream(); OutputStream outputStream = clientSocket.getOutputStream())
            {
                Message request = new Message();
                request.readFrom(inputStream);
                System.out.println("received request: " + request);
                Message response = methodHandlers.get(request.getHeader()).apply(request);
                response.writeTo(outputStream);
                System.out.println("sent response: " + response);
            }
            catch (IOException e)
            {
                System.out.println(e.getMessage());
            }
        }
    }
}
