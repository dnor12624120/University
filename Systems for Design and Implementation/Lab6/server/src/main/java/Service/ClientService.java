package Service;

import Domain.Entities.Client;
import Domain.Validators.RepositoryException;
import Domain.Validators.ValidatorException;
import Repository.SortingRepository;
import Utility.Utility;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

public class ClientService
{
    private final SortingRepository<Integer, Client> clientRepository;
    private final ExecutorService executorService;

    public ClientService(SortingRepository<Integer, Client> clientRepository, ExecutorService executorService)
    {
        this.clientRepository = clientRepository;
        this.executorService = executorService;
    }

    public Future<Boolean> addClient(Client client) throws ValidatorException, RepositoryException
    {
        return executorService.submit(() -> !clientRepository.save(client).isPresent());
    }

    public Future<Boolean> deleteClient(int clientID) throws RepositoryException
    {
        return executorService.submit(() -> clientRepository.delete(clientID).isPresent());
    }

    public Future<Boolean> updateClient(Client client) throws RepositoryException, ValidatorException
    {
        return executorService.submit(() -> clientRepository.update(client).isPresent());
    }

    public Future<Set<Client>> getAllClients()
    {
        return executorService.submit(() -> Utility.iterableToSet(clientRepository.findAll()));
    }

}
