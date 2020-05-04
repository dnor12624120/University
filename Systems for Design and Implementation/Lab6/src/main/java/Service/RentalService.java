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
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class RentalService
{
    private SortingRepository<Integer, Rental> rentalRepository;
    private SortingRepository<Integer, Client> clientRepository;
    private SortingRepository<Integer, Movie> movieRepository;

    public RentalService(SortingRepository<Integer, Rental> rentalRepository,
                         SortingRepository<Integer, Client> clientRepository,
                         SortingRepository<Integer, Movie> movieRepository)
    {
        this.rentalRepository = rentalRepository;
        this.clientRepository = clientRepository;
        this.movieRepository = movieRepository;
    }

    public void addRental(Rental rental) throws RepositoryException, IOException, ParserConfigurationException, TransformerException, SAXException, RepositoryException, SQLException, NoSuchFieldException, IllegalAccessException {
        checkIfRentalExists(rental.getClientID(), rental.getMovieID());
        rentalRepository.save(rental).ifPresent(c -> { throw new RepositoryException("Cannot add specified rental."); });
    }

    public void deleteRental(int rentalID) throws RepositoryException, IOException, ParserConfigurationException, TransformerException, SAXException, RepositoryException, SQLException {
        rentalRepository.delete(rentalID).orElseThrow(() -> new RepositoryException("Cannot delete specified rental"));
    }

    private void checkIfRentalExists(int clientID, int movieID) throws SQLException {
        Optional<Client> clientQueryResult = clientRepository.findOne(clientID);
        clientQueryResult.orElseGet(() -> { throw new RepositoryException("No client with given ID exists."); });
        Optional<Movie> movieQueryResult = movieRepository.findOne(movieID);
        movieQueryResult.orElseGet(() -> { throw new RepositoryException("No movie with given ID exists."); });
    }

    public Set<Rental> getAllRentals() throws NoSuchFieldException, IllegalAccessException, SQLException {
        return Utility.iterableToSet(rentalRepository.findAll());
    }

    public Set<Rental> filterRentals(Predicate<Rental> predicate) throws SQLException, NoSuchFieldException, IllegalAccessException { return Utility.iterableToSet(rentalRepository.filter(predicate));}

    private Map<Integer, Long> groupRentalsByCount() throws IllegalAccessException, NoSuchFieldException, SQLException {
        return getAllRentals().
               stream().
               map(Rental::getMovieID).
               collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
    }

    public int getMaxNumOfRentalsPerMovie() throws RepositoryException, IllegalAccessException, NoSuchFieldException, SQLException {
        Optional<Long> maxNumOfRentals = groupRentalsByCount().values().stream().max(Long::compare);
        maxNumOfRentals.orElseGet(() -> { throw new RepositoryException("No rentals to filter."); });
        return maxNumOfRentals.get().intValue();
    }

    public Set<Integer> getMostRentedMovieIDs() throws IllegalAccessException, NoSuchFieldException, SQLException {
        return groupRentalsByCount().
                entrySet().
                stream().
                filter(entry -> {
                    try {
                        return (entry.getValue().equals(Integer.toUnsignedLong(getMaxNumOfRentalsPerMovie())));
                    } catch (IllegalAccessException | NoSuchFieldException | SQLException e) {
                        e.printStackTrace();
                    }
                    return false;
                }).
                map(Map.Entry::getKey).
                collect(Collectors.toSet());
    }
}
