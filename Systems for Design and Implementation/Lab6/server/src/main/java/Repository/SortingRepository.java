package Repository;

import Domain.Entities.BaseEntity;
import Utility.Sort;

import java.io.Serializable;
import java.sql.SQLException;

public interface SortingRepository<ID extends Serializable, T extends BaseEntity<ID>> extends FilterableRepository<ID, T>
{
    Iterable<T> findAll(Sort sort) throws SQLException, NoSuchFieldException, IllegalAccessException;
}