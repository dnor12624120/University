package Server;

import Domain.Entities.Client;
import Domain.Entities.Movie;
import Domain.Entities.Rental;
import Service.ClientService;
import Service.MovieService;
import Service.RentalService;
import Utility.Utility;
import Communication.Message;

import java.sql.SQLException;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ExecutionException;

public class MessageHandler
{
    ClientService clientService;
    MovieService movieService;
    RentalService rentalService;

    public MessageHandler(ClientService clientService, MovieService movieService, RentalService rentalService)
    {
        this.clientService = clientService;
        this.movieService = movieService;
        this.rentalService = rentalService;
    }

    public Message addClient(Message request)
    {
        Client parameter = Utility.stringToClient(request.getBody());
        try
        {
            return clientService.addClient(parameter).get() ? new Message("ok", "") : new Message("error", "Client already exists");
        }
        catch (InterruptedException | ExecutionException | RuntimeException e)
        {
            return new Message("error", e.getCause().getMessage());
        }
    }

    public Message deleteClient(Message request)
    {
        int clientID = Integer.parseInt(request.getBody());
        try
        {
            return clientService.deleteClient(clientID).get() ? new Message("ok", "") : new Message("error", "Client does not exist");
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getMessage());
        }
    }

    public Message updateClient(Message request)
    {
        Client parameter = Utility.stringToClient(request.getBody());
        try
        {
            return clientService.updateClient(parameter).get() ? new Message("ok", "") : new Message("error", "Client does not exist");
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getMessage());
        }
    }

    public Message getAllClients(Message request)
    {
        try
        {
            Set<Client> result =  clientService.getAllClients().get();
            String messageBody = result.stream()
                    .map(Client::toString)
                    .reduce("", (s,e) -> s + e + "|");
            return new Message("ok", messageBody);
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getMessage());
        }
    }

    public Message addMovie(Message request)
    {
        Movie parameter = Utility.stringToMovie(request.getBody());
        try
        {
            return movieService.addMovie(parameter).get() ? new Message("ok", "") : new Message("error", "Movie already exists");
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getMessage());
        }
    }

    public Message deleteMovie(Message request)
    {
        int movieID = Integer.parseInt(request.getBody());
        try
        {
            return movieService.deleteMovie(movieID).get() ? new Message("ok", "") : new Message("error", "Movie does not exist");
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getCause().getMessage());
        }
    }

    public Message updateMovie(Message request)
    {
        Movie parameter = Utility.stringToMovie(request.getBody());
        try
        {
            return movieService.updateMovie(parameter).get() ? new Message("ok", "") : new Message("error", "Movie does not exist");
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getCause().getMessage());
        }
    }

    public Message getAllMovies(Message request)
    {
        try
        {
            Set<Movie> result =  movieService.getAllMovies().get();
            String messageBody = result.stream()
                    .map(Movie::toString)
                    .reduce("", (s,e) -> s + e + "|");
            return new Message("ok", messageBody);
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getCause().getMessage());
        }
    }

    public Message addRental(Message request)
    {
        Rental parameter = Utility.stringToRental(request.getBody());
        try
        {
            return rentalService.addRental(parameter).get() ? new Message("ok", "ok") : new Message("error", "Rental already exists");
        }
        catch (InterruptedException | ExecutionException | SQLException e)
        {
            return new Message("error", e.getCause().getMessage());
        }
    }

    public Message deleteRental(Message request)
    {
        int rentalID = Integer.parseInt(request.getBody());
        try
        {
            return rentalService.deleteRental(rentalID).get() ? new Message("ok", "ok") : new Message("error", "Rental does not exist");
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getCause().getMessage());
        }
    }

    public Message getAllRentals(Message request)
    {
        try
        {
            Set<Rental> result =  rentalService.getAllRentals().get();
            String messageBody = result.stream()
                    .map(Rental::toString)
                    .reduce("", (s,e) -> s + e + "|");
            return new Message("ok", messageBody);
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getMessage());
        }
    }

    public Message getMostRentedMovies(Message request)
    {
        try
        {
            Set<Integer> filteredRentals = rentalService.getMostRentedMovieIDs();
            Set<Movie> mostRentedMovies = movieService.getMostRentedMovies(filteredRentals).get();
            String messageBody = mostRentedMovies.stream()
                    .map(Movie::toString)
                    .reduce("", (s,e) -> s + e + "|");
            return new Message("ok", messageBody);
        }
        catch(Exception e)
        {
            return new Message("error", e.getMessage());
        }
    }

    public Message getMoviesSortedByGenre(Message request)
    {
        try
        {
            List<Movie> sortedMovies = movieService.getMoviesSortedByGenre().get();
            String messageBody = sortedMovies.stream()
                    .map(Movie::toString)
                    .reduce("", (s,e) -> s + e + "|");
            return new Message("ok", messageBody);
        }
        catch (InterruptedException | ExecutionException e)
        {
            return new Message("error", e.getMessage());
        }
    }
}

