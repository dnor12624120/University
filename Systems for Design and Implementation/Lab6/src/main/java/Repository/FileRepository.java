package Repository;

import Domain.Entities.BaseEntity;
import Domain.Validators.ValidatorException;
import Utility.Sort;
import Utility.Utility;
import Domain.Validators.Validator;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.*;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Optional;
import java.util.function.Supplier;

public class FileRepository<ID extends Serializable, T extends BaseEntity<ID>> extends InMemoryRepository<ID, T> implements SortingRepository<ID, T>
{
    private String filepath;
    private Supplier<? extends T> constructor;

    public FileRepository(String filepath, Validator<T> validator, Supplier<? extends  T> constructor) throws IOException, TransformerException, ParserConfigurationException, SAXException
    {
        super(validator);
        this.filepath = filepath;
        this.constructor = constructor;
        loadFromFile();
    }

    private void loadFromFile() throws IOException, ParserConfigurationException, TransformerException, SAXException
    {
        try (BufferedReader reader = new BufferedReader(new FileReader(filepath)))
        {
            while(true)
            {
                try
                {
                    T entity = constructor.get();
                    entity.readFromFile(reader);
                    super.save(entity);
                }
                catch (NumberFormatException exception)
                {
                    break;
                }
            }
        }
    }

    private void saveToFile() throws IOException
    {
        Utility.clearContentsOfFile(filepath);
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filepath)))
        {
            super.entities.values().forEach(entity -> {
                try {
                    Field idField = entity.getClass().getSuperclass().getDeclaredField("id");
                    writer.write(idField.get(entity).toString());
                } catch (NoSuchFieldException | IllegalAccessException | IOException e) {
                    e.printStackTrace();
                }
                ArrayList<Field> fields = new ArrayList<>(Arrays.asList(entity.getClass().getDeclaredFields()));
                fields.forEach(field -> {
                    field.setAccessible(true);
                    try {
                        writer.write(field.get(entity).toString());
                    } catch (IllegalAccessException | IOException e) {
                        e.printStackTrace();
                    }
                    field.setAccessible(false);
                });
            });
        }
    }

    @Override
    public Optional<T> save(T entity) throws ValidatorException, IOException, ParserConfigurationException, TransformerException, SAXException {
        Optional<T> result = super.save(entity);
        saveToFile();
        return result;
    }

    @Override
    public Optional<T> delete(ID id) throws IOException, ParserConfigurationException, TransformerException, SAXException {
        Optional<T> result = super.delete(id);
        saveToFile();
        return result;
    }

    @Override
    public Optional<T> update(T entity) throws ValidatorException, IOException, ParserConfigurationException, TransformerException, SAXException {
        Optional<T> result = super.update(entity);
        saveToFile();
        return result;
    }

    @Override
    public Iterable<T> findAll(Sort sort) {
        return null;
    }
}
