package Service;

import Domain.Entities.Client;
import Utility.Utility;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Repository.SortingRepository;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;
import java.util.Set;

public class ClientService
{
    private SortingRepository<Integer, Client> clientRepository;

    public ClientService(SortingRepository<Integer, Client> clientRepository)
    {
        this.clientRepository = clientRepository;
    }

    public void addClient(Client client) throws ValidatorException, IOException, ParserConfigurationException, TransformerException, SAXException, SQLException, NoSuchFieldException, RepositoryException, IllegalAccessException {
        clientRepository.save(client).ifPresent(c -> { throw new RepositoryException("Cannot add specified client."); });
    }

    public void deleteClient(int clientID) throws RepositoryException, IOException, ParserConfigurationException, TransformerException, SAXException, SQLException {
        clientRepository.delete(clientID).orElseThrow(() -> new RepositoryException("Cannot delete specified client"));
    }

    public void updateClient(Client client) throws RepositoryException, ValidatorException, IOException, ParserConfigurationException, TransformerException, SAXException, SQLException, NoSuchFieldException, IllegalAccessException {
        clientRepository.update(client).orElseThrow(() -> new RepositoryException("Cannot update specified client"));
    }

    public Set<Client> getAllClients() throws NoSuchFieldException, IllegalAccessException, SQLException {
        return Utility.iterableToSet(clientRepository.findAll());
    }

}
