package Service;

import Communication.Message;
import Domain.Entities.Client;
import Domain.Validators.CommunicationException;
import Client.TcpClient;
import Utility.Utility;

import java.util.Arrays;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.stream.Collectors;

public class ClientService
{
    private final TcpClient tcpClient;
    private final ExecutorService executorService;

    public ClientService(ExecutorService executorService, TcpClient tcpClient)
    {
        this.executorService = executorService;
        this.tcpClient = tcpClient;
    }

    public Future<Boolean> addClient(Client client) throws CommunicationException
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "add client", client.toString());
        Message response = tcpClient.sendAndReceive(message);
        return wasOperationSuccessful(response.getHeader());
    }

    public Future<Boolean> deleteClient(int clientID) throws CommunicationException
    {
        Message message = new Message(tcpClient.getServerEndpoint(),"delete client", Integer.toString(clientID));
        Message response = tcpClient.sendAndReceive(message);
        return wasOperationSuccessful(response.getHeader());
    }

    public Future<Boolean> updateClient(Client client) throws CommunicationException
    {
        Message message = new Message(tcpClient.getServerEndpoint(),"update client", client.toString());
        Message response = tcpClient.sendAndReceive(message);
        return wasOperationSuccessful(response.getHeader());
    }

    public Future<Set<Client>> getAllClients()
    {
        Message message = new Message(tcpClient.getServerEndpoint(),"get all clients", "");
        Message response = tcpClient.sendAndReceive(message);
        return clientsToSet(response.getBody());
    }

    private Future<Boolean> wasOperationSuccessful(String messageHeader)
    {
        return executorService.submit(() -> !messageHeader.equals("error"));
    }

    private Future<Set<Client>> clientsToSet(String messageBody)
    {
        String[] tokens = messageBody.split("\\|");
        Set<Client> clients = Arrays.stream(tokens).map(Utility::stringToClient).collect(Collectors.toSet());
        return executorService.submit(() -> clients);
    }
}
