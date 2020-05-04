package Service;

import Domain.Entities.Movie;
import Domain.Validators.CommunicationException;
import Utility.Utility;
import Client.TcpClient;
import Communication.Message;

import java.util.Arrays;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.stream.Collectors;

public class MovieService
{
    private final TcpClient tcpClient;
    private final ExecutorService executorService;

    public MovieService(ExecutorService executorService, TcpClient tcpClient)
    {
        this.executorService = executorService;
        this.tcpClient = tcpClient;
    }

    public Future<Boolean> addMovie(Movie movie) throws CommunicationException
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "add movie", movie.toString());
        Message response = tcpClient.sendAndReceive(message);
        return wasOperationSuccessful(response.getHeader());
    }

    public Future<Boolean> deleteMovie(int movieID) throws CommunicationException
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "delete movie", Integer.toString(movieID));
        Message response = tcpClient.sendAndReceive(message);
        return wasOperationSuccessful(response.getHeader());
    }

    public Future<Boolean> updateMovie(Movie movie) throws CommunicationException
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "update movie", movie.toString());
        Message response = tcpClient.sendAndReceive(message);
        return wasOperationSuccessful(response.getHeader());
    }

    public Future<Set<Movie>> getAllMovies()
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "get all movies", "");
        Message response = tcpClient.sendAndReceive(message);
        return moviesToSet(response.getBody());
    }

    public Future<Set<Movie>> getMostRentedMovies()
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "get most rented movies", "");
        Message response = tcpClient.sendAndReceive(message);
        return moviesToSet(response.getBody());
    }

    public Future<List<Movie>> getMoviesSortedByGenre()
    {
        Message message = new Message(tcpClient.getServerEndpoint(), "get movies sorted by genre", "");
        Message response = tcpClient.sendAndReceive(message);
        return moviesToList(response.getBody());
    }

    private Future<Boolean> wasOperationSuccessful(String messageHeader)
    {
        return executorService.submit(() -> !messageHeader.equals("error"));
    }

    private Future<Set<Movie>> moviesToSet(String messageBody)
    {
        String[] tokens = messageBody.split("\\|");
        Set<Movie> movies = Arrays.stream(tokens).map(Utility::stringToMovie).collect(Collectors.toSet());
        return executorService.submit(() -> movies);
    }

    private Future<List<Movie>> moviesToList(String messageBody)
    {
        String[] tokens = messageBody.split("\\|");
        List<Movie> movies = Arrays.stream(tokens).map(Utility::stringToMovie).collect(Collectors.toList());
        return executorService.submit(() -> movies);
    }
}
