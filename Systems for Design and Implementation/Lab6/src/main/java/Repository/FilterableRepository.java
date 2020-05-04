package Repository;

import Domain.Entities.BaseEntity;

import java.io.Serializable;
import java.sql.SQLException;
import java.util.function.Predicate;

public interface FilterableRepository<ID extends Serializable, T extends BaseEntity<ID>> extends Repository<ID, T>
{
    Iterable<T> filter(Predicate<T> predicate) throws SQLException, NoSuchFieldException, IllegalAccessException;
}
