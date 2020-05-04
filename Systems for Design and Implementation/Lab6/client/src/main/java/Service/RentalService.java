package Service;

import Client.TcpClient;
import Communication.Message;
import Domain.Entities.Rental;
import Utility.Utility;

import java.util.Arrays;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.stream.Collectors;

public class RentalService
{
    private final TcpClient tcpClient;
    private final ExecutorService executorService;

    public RentalService(ExecutorService executorService, TcpClient tcpClient)
    {
        this.executorService = executorService;
        this.tcpClient = tcpClient;
    }

    public Future<Boolean> addRental(Rental rental)
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "add rental", rental.toString());
        Message response = tcpClient.sendAndReceive(message);
        return wasOperationSuccessful(response.getHeader());
    }

    public Future<Boolean> deleteRental(int rentalID)
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "delete rental", Integer.toString(rentalID));
        Message response = tcpClient.sendAndReceive(message);
        return wasOperationSuccessful(response.getHeader());
    }

    public Future<Set<Rental>> getAllRentals()
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "get all rentals", "");
        Message response = tcpClient.sendAndReceive(message);
        return rentalsToSet(response.getBody());
    }


    private Future<Boolean> wasOperationSuccessful(String messageHeader)
    {
        return executorService.submit(() -> !messageHeader.equals("error"));
    }

    private Future<Set<Rental>> rentalsToSet(String messageBody)
    {
        String[] tokens = messageBody.split("\\|");
        Set<Rental> rentals = Arrays.stream(tokens).map(Utility::stringToRental).collect(Collectors.toSet());
        return executorService.submit(() -> rentals);
    }
}