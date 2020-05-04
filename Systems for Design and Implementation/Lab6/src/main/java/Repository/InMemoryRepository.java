package Repository;

import Domain.Entities.BaseEntity;
import Domain.Validators.Validator;
import Domain.Validators.ValidatorException;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.io.Serializable;
import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class InMemoryRepository<ID extends Serializable, T extends BaseEntity<ID>> implements FilterableRepository<ID, T> {
    protected Map<ID, T> entities;
    protected Validator<T> validator;

    public InMemoryRepository(Validator<T> validator)
    {
        this.validator = validator;
        entities = new HashMap<>();
    }

    @Override
    public Optional<T> findOne(ID id)
    {
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }
        return Optional.ofNullable(entities.get(id));
    }

    @Override
    public Iterable<T> findAll()
    {
        return new HashSet<>(entities.values());
    }

    @Override
    public Iterable<T> filter(Predicate<T> predicate)
    {
        return entities.values().stream().filter(predicate).collect(Collectors.toSet());
    }

    @Override
    public Optional<T> save(T entity) throws ValidatorException, IOException, TransformerException, SAXException, ParserConfigurationException {
        if (entity == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }
        return Optional.ofNullable(entities.putIfAbsent(entity.getID(), entity));
    }

    @Override
    public Optional<T> delete(ID id) throws IOException, TransformerException, SAXException, ParserConfigurationException {
        if (id == null)
        {
            throw new IllegalArgumentException("id must not be null");
        }
        return Optional.ofNullable(entities.remove(id));
    }

    @Override
    public Optional<T> update(T entity) throws ValidatorException, IOException, TransformerException, SAXException, ParserConfigurationException {
        if (entity == null)
        {
            throw new IllegalArgumentException("entity must not be null");
        }
        validator.validate(entity);
        return Optional.ofNullable(entities.computeIfPresent(entity.getID(), (k, v) -> entity));
    }
}
