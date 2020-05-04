package Service;

import Domain.Entities.Client;
import Domain.Entities.Movie;
import Domain.Entities.Rental;
import Domain.Validators.RepositoryException;
import Repository.SortingRepository;
import Utility.Utility;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class RentalService
{
    private final SortingRepository<Integer, Rental> rentalRepository;
    private final SortingRepository<Integer, Client> clientRepository;
    private final SortingRepository<Integer, Movie> movieRepository;
    ExecutorService executorService;

    public RentalService(SortingRepository<Integer, Rental> rentalRepository,
                         SortingRepository<Integer, Client> clientRepository,
                         SortingRepository<Integer, Movie> movieRepository,
                         ExecutorService executorService)
    {
        this.rentalRepository = rentalRepository;
        this.clientRepository = clientRepository;
        this.movieRepository = movieRepository;
        this.executorService = executorService;
    }

    public Future<Boolean> addRental(Rental rental) throws RepositoryException, SQLException
    {
        checkIfRentalExists(rental.getClientID(), rental.getMovieID());
        return executorService.submit(() -> !rentalRepository.save(rental).isPresent());
    }

    public Future<Boolean> deleteRental(int rentalID) throws RepositoryException
    {
        return executorService.submit(() -> rentalRepository.delete(rentalID).isPresent());
    }

    private void checkIfRentalExists(int clientID, int movieID) throws SQLException
    {
        Optional<Client> clientQueryResult = clientRepository.findOne(clientID);
        clientQueryResult.orElseGet(() -> { throw new RepositoryException("No client with given ID exists."); });
        Optional<Movie> movieQueryResult = movieRepository.findOne(movieID);
        movieQueryResult.orElseGet(() -> { throw new RepositoryException("No movie with given ID exists."); });
    }

    public Future<Set<Rental>> getAllRentals()
    {
        return executorService.submit(() -> Utility.iterableToSet(rentalRepository.findAll()));
    }

    public Set<Rental> filterRentals(Predicate<Rental> predicate) throws SQLException, NoSuchFieldException, IllegalAccessException { return Utility.iterableToSet(rentalRepository.filter(predicate));}

    private Map<Integer, Long> groupRentalsByCount() throws ExecutionException, InterruptedException
    {
        return getAllRentals().
               get().
               stream().
               map(Rental::getMovieID).
               collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
    }

    public int getMaxNumOfRentalsPerMovie() throws RepositoryException, ExecutionException, InterruptedException
    {
        Optional<Long> maxNumOfRentals = groupRentalsByCount().values().stream().max(Long::compare);
        maxNumOfRentals.orElseGet(() -> { throw new RepositoryException("No rentals to filter."); });
        return maxNumOfRentals.get().intValue();
    }

    public Set<Integer> getMostRentedMovieIDs() throws ExecutionException, InterruptedException
    {
        return groupRentalsByCount().
                entrySet().
                stream().
                filter(entry -> {
                    try
                    {
                        return (entry.getValue().equals(Integer.toUnsignedLong(getMaxNumOfRentalsPerMovie())));
                    }
                    catch (ExecutionException | InterruptedException ignored)
                    {
                    }
                    return false;
                }).
                map(Map.Entry::getKey).
                collect(Collectors.toSet());
    }
}
