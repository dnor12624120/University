package Repository;

import Domain.Entities.BaseEntity;
import Domain.Validators.ValidatorException;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.io.Serializable;
import java.sql.SQLException;
import java.util.Optional;

public interface Repository<ID extends Serializable, T extends BaseEntity<ID>>
{

    Optional<T> findOne(ID id) throws SQLException;

    Iterable<T> findAll() throws SQLException, NoSuchFieldException, IllegalAccessException;

    Optional<T> save(T entity) throws ValidatorException, SQLException, IllegalAccessException, NoSuchFieldException;

    Optional<T> delete(ID id) throws IOException, SQLException;

    Optional<T> update(T entity) throws ValidatorException, SQLException, NoSuchFieldException, IllegalAccessException;

}
