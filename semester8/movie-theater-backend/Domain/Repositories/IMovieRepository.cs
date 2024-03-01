using Domain.Entities;

namespace Domain.Repositories;

public interface IMovieRepository
{
    public Task<IEnumerable<Movie>> Get(MovieSearchParams parameters);

    public Task<Movie?> GetById(int id);

    public Task Add(Movie movie);

    public void Save();
}