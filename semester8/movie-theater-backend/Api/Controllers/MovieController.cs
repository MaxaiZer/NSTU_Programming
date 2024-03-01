using Microsoft.AspNetCore.Mvc;
using Application.Dto;
using Domain.Repositories;
using Application.Services.Interfaces;

namespace Api.Controllers;

[ApiController]
[Route("api/movies")]
public class MovieController : ControllerBase
{
    private readonly IMovieService _movieService;

    public MovieController(IMovieService movieService)
    {
        _movieService = movieService;    
    }

    [HttpGet]
    public async Task<ActionResult<IEnumerable<MovieDto>>> Get([FromQuery]MovieSearchParams parameters)
    {
        return new JsonResult(await _movieService.GetMoviesAsync(parameters));
    }

    [HttpGet("{id}")]
    public async Task<IActionResult> Get(int id)
    {
        var response = await _movieService.GetMovieByIdAsync(id);
        if (response == null)
            return NotFound();

        return new JsonResult(response);
    }

/*
    [HttpGet("{id}/stream")]
    public async Task<FileStreamResult> Stream(int id)
    {
        string _videoPath = "123";
        string videoName = "123";
        var videoFileStream = new FileStream(_videoPath, FileMode.Open, FileAccess.Read);

        var contentType = "video/mp4"; 

        return new FileStreamResult(videoFileStream, contentType)
        {
            FileDownloadName = videoName,
            EnableRangeProcessing = true
        };
    }
*/
    [HttpPost]
    public async Task<IActionResult> Post([FromForm]MovieUploadDto movieInfo)
    {
        if (movieInfo.Image == null)
        {
            return BadRequest("Image was not uploaded.");
        }

        if (movieInfo.Movie == null || movieInfo.Movie.Length == 0)
        {
            return BadRequest("Movie was not uploaded.");
        }

        await _movieService.UploadMovieAsync(movieInfo);
        return Ok("Movie uploaded successfully.");
    }
}
