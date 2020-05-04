import Domain.DatabaseConfig;
import Domain.Entities.Client;
import Domain.Entities.Movie;
import Domain.Entities.Rental;
import Domain.Validators.GenericValidator;
import Domain.Validators.Validator;
import Repository.DatabaseRepository;
import Repository.SortingRepository;
import Server.MessageHandler;
import Server.TcpServer;
import Service.ClientService;
import Service.MovieService;
import Service.RentalService;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.function.Function;

public class ServerMain
{
    private static ClientService clientService;
    private static MovieService movieService;
    private static RentalService rentalService;
    public static void main(String[] args)
    {
        ExecutorService executorService = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());

        ArrayList<Function<Movie, String>> moviePredicates = new ArrayList<>();
        moviePredicates.add(movie -> movie.getName().isEmpty() ? "Movie name cannot be empty!" : "");
        moviePredicates.add(movie -> movie.getGenre().isEmpty() ? "Movie genre cannot be empty!" : "");
        moviePredicates.add(movie -> movie.getDescription().isEmpty() ? "Movie description cannot be empty!" : "");
        Validator<Movie> movieValidator = new GenericValidator<>(moviePredicates);

        ArrayList<Function<Client, String>> clientPredicates = new ArrayList<>();
        clientPredicates.add(client -> client.getName().isEmpty() ? "Client name cannot be empty!" : "");
        clientPredicates.add(client -> client.getAge() < 0 ? "Client age cannot be negative!" : "");
        Validator<Client> clientValidator = new GenericValidator<>(clientPredicates);

        DatabaseConfig movieRepositoryConfig = new DatabaseConfig("jdbc:postgresql://localhost:5432/rental_app", "postgres", "hahaxd123", "public.\"Movie\"");
        DatabaseConfig clientRepositoryConfig = new DatabaseConfig("jdbc:postgresql://localhost:5432/rental_app", "postgres", "hahaxd123", "public.\"Client\"");
        DatabaseConfig rentalRepositoryConfig = new DatabaseConfig("jdbc:postgresql://localhost:5432/rental_app", "postgres", "hahaxd123", "public.\"Rental\"");

        try
        {
            SortingRepository<Integer, Movie> movieRepository = new DatabaseRepository<>(movieRepositoryConfig, Movie::new, movieValidator);
            movieService = new MovieService(movieRepository, executorService);

            SortingRepository<Integer, Client> clientRepository = new DatabaseRepository<Integer, Client>(clientRepositoryConfig, Client::new, clientValidator);
            clientService = new ClientService(clientRepository, executorService);

            SortingRepository<Integer, Rental> rentalRepository = new DatabaseRepository<>(rentalRepositoryConfig, Rental::new, new GenericValidator<>(new ArrayList<>()));
            rentalService = new RentalService(rentalRepository, clientRepository, movieRepository, executorService);
        }
        catch (NoSuchFieldException exception) {
            System.out.println(exception.getMessage());
        }

        MessageHandler messageHandler = new MessageHandler(clientService, movieService, rentalService);
        TcpServer server = new TcpServer(executorService, "11011");

        server.addHandler("add client", messageHandler::addClient);
        server.addHandler("delete client", messageHandler::deleteClient);
        server.addHandler("update client", messageHandler::updateClient);
        server.addHandler("get all clients", messageHandler::getAllClients);

        server.addHandler("add movie", messageHandler::addMovie);
        server.addHandler("delete movie", messageHandler::deleteMovie);
        server.addHandler("update movie", messageHandler::updateMovie);
        server.addHandler("get all movies", messageHandler::getAllMovies);

        server.addHandler("add rental", messageHandler::addRental);
        server.addHandler("delete rental", messageHandler::deleteRental);
        server.addHandler("get all rentals", messageHandler::getAllRentals);

        server.addHandler("get most rented movies", messageHandler::getMostRentedMovies);
        server.addHandler("get movies sorted by genre", messageHandler::getMoviesSortedByGenre);

        System.out.println("Server started");
        server.startServer();
        executorService.shutdown();
        System.out.println("Server stopped");
    }
}
