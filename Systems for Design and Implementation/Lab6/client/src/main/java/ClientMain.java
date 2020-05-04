import Communication.Endpoint;

import Service.ClientService;
import Service.MovieService;
import Service.RentalService;
import View.Commands.*;
import View.Console.ConsoleMenu;
import java.util.HashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import Client.TcpClient;

public class ClientMain
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
        TcpClient tcpClient = new TcpClient(new Endpoint("localhost", "11011"));
        ExecutorService executorService = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
        movieService = new MovieService(executorService, tcpClient);
        clientService = new ClientService(executorService, tcpClient);
        rentalService = new RentalService(executorService, tcpClient);
    }

    private static void initConsoleCommands()
    {
        commands = new HashMap<>();
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
        commands.put("M", new ViewMostRentedMoviesCommand("View most rented movies", "", movieService));
        commands.put("N", new ViewMoviesSortedByGenreCommand("View movies sorted by genre", "", movieService));
    }
}
