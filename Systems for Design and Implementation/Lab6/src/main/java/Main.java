import Domain.Entities.Client;
import Domain.DatabaseConfig;
import Domain.Entities.Movie;
import Domain.Entities.Rental;
import Domain.Validators.GenericValidator;
import Domain.Validators.Validator;
import Repository.DatabaseRepository;
import Repository.SortingRepository;
import Service.ClientService;
import Service.MovieService;
import Service.RentalService;
import View.Commands.*;
import View.Console.ConsoleMenu;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.function.Function;

public class Main
{
    private static HashMap<String, MenuCommand> commands;

    private static MovieService movieService;
    private static ClientService clientService;
    private static RentalService rentalService;

    public static void main(String[] args)
    {
        initMembers();
        initConsoleCommands();

        ConsoleMenu menu = new ConsoleMenu(commands, true);
        menu.run();
    }

    private static void initMembers()
    {
        commands = new HashMap<>();

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
            movieService = new MovieService(movieRepository);

            SortingRepository<Integer, Client> clientRepository = new DatabaseRepository<Integer, Client>(clientRepositoryConfig, Client::new, clientValidator);
            clientService = new ClientService(clientRepository);

            SortingRepository<Integer, Rental> rentalRepository = new DatabaseRepository<>(rentalRepositoryConfig, Rental::new, new GenericValidator<>(new ArrayList<>()));
            rentalService = new RentalService(rentalRepository, clientRepository, movieRepository);
        }
        catch (NoSuchFieldException exception) {
            System.out.println(exception.getMessage());
        }
    }

    private static void initConsoleCommands()
    {
        commands.put("A", new ExitCommand("Exit menu", ""));
        commands.put("B", new AddMovieCommand("Add movie", "", movieService));
        commands.put("C", new AddClientCommand("Add client", "", clientService));
        commands.put("D", new AddRentalCommand("Add rental", "", rentalService));
        commands.put("E", new DeleteMovieCommand("Delete movie", "", movieService));
        commands.put("F", new DeleteClientCommand("Delete client", "", clientService));
        commands.put("G", new DeleteRentalCommand("Delete rental", "", rentalService));
        commands.put("H", new UpdateMovieCommand("Update movie", "", movieService));
        commands.put("I", new UpdateClientCommand("Update client", "", clientService));
        commands.put("J", new ViewAllMoviesCommand("View all movies", "", movieService));
        commands.put("K", new ViewAllClientsCommand("View all clients", "", clientService));
        commands.put("L", new ViewAllRentalsCommand("View all rentals", "", rentalService));
        commands.put("M", new ViewMostRentedMoviesCommand("View most rented movies", "", rentalService, movieService));
        commands.put("N", new ViewMoviesSortedByGenreCommand("View movies sorted by genre", "", movieService));
    }
}
